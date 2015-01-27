using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SCADA;
using SCADA.Data;
using SCADA.Data.Types;

namespace SCADA.RemoteObjects
{
	class PLC
	{
		public PLCDataProvider Provider;

		public DataStorage<CommunicationData> DataOut;
		public PLCDataConsumer Consumer;

		private SerialPort Connection;

		private byte CorrectHeaderFlag = 0xAA;
		private ushort CorrectFooterFlag = 0x5555;

		public byte Address;

		public PLC(byte address, string portName, int baudRate)
		{
			try
			{
				Connection = new SerialPort(portName, baudRate);
				Connection.Open();
			} 
			catch(Exception e)
			{
				Console.WriteLine(e.Message);
			}
			
			Provider = new PLCDataProvider(this);

			DataOut = new DataStorage<CommunicationData>();
			Consumer = new PLCDataConsumer(this);

			Consumer.AttachStorageSource(DataOut);

			Address = address;
		}

		~PLC()
		{
			Connection.Close();
		}

		public class PLCDataProvider : DataProvider<CommunicationData>
		{
			private PLC Parent;

			public PLCDataProvider(PLC parent)
			{
				Parent = parent;
			}

			public override void ProvideData()
			{
				if (!Parent.Connection.IsOpen)
				{
					return;
				}

				byte[] headerData = new byte[6];

				byte headerFlag;
				byte address;
				byte remoteAddress;
				ushort comId;
				short id;
				ushort payloadSize;
				byte[] payload;

				byte[] footerData = new byte[2];
				int footerFlag;

				while (Parent.Connection.BytesToRead > 8)
				{
					Parent.Connection.Read(headerData, 0, 6);

					headerFlag = headerData[0];

					if (headerFlag == Parent.CorrectHeaderFlag)
					{
						address = headerData[1];
						address &= 0xF0;
						remoteAddress = headerData[1];
						remoteAddress -= address;
						address >>= 4;

						payloadSize = (ushort)headerData[2];
						comId = (ushort)headerData[3];
						id = BitConverter.ToInt16(headerData, 4);

						payload = new byte[payloadSize];

						Parent.Connection.Read(payload, 0, payloadSize);
						Parent.Connection.Read(footerData, 0, 2);

						footerFlag = BitConverter.ToUInt16(footerData, 0);

						if (footerFlag == Parent.CorrectFooterFlag)
						{
							AddData(new CommunicationData(DateTime.Now, address, remoteAddress, comId, id, payload));
						}
						else
						{
							Parent.Connection.DiscardInBuffer();
						}
					}
					else
					{
						Parent.Connection.DiscardInBuffer();
					}
				}
			}

			private void AddData(CommunicationData data)
			{
				foreach (var dataStorage in Destinations)
				{
					dataStorage.Add(data);
				}
			}
		}

		public class PLCDataConsumer : DataConsumer<CommunicationData>
		{
			private PLC Parent;

			public PLCDataConsumer(PLC parent)
			{
				Parent = parent;
			}

			public override bool ConsumeEntry(CommunicationData entry)
			{
				// todo

				return true;
			}
		}

	}
}
