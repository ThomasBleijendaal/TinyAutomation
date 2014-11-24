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
		public class PLCDataProvider : DataProvider<RawData>
		{
			private PLC Parent;

			public PLCDataProvider(PLC parent)
			{
				Parent = parent;
			}

			public override void ProvideData()
			{
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
							AddData(new RawData(DateTime.Now, comId, id, payload));
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

			private void AddData(RawData entity)
			{
				foreach (DataStorage<RawData> dataStorage in DataStoragesOutput)
				{
					dataStorage.Add(entity);
				}
			}
		}

		public PLCDataProvider Provider;

		private SerialPort Connection;

		private byte CorrectHeaderFlag = 0xAA;
		private ushort CorrectFooterFlag = 0x5555;

		private byte Address;

		public PLC(byte address, string portName, int baudRate)
		{
			Connection = new SerialPort(portName, baudRate);
			Connection.Open();
			
			Provider = new PLCDataProvider(this);

			Address = address;
		}

		~PLC()
		{
			Connection.Close();
		}
	}
}
