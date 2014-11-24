using System;
using System.Collections.Generic;
using System.Linq;
using System.IO.Ports;

using SCADA.Data;
using SCADA.Data.Types;

namespace SCADA
{
	class PLCConnection: DataProvider<RawData>
	{
		private SerialPort connection;

		private ushort correctHeaderFlag = 0xAAAA;
		private ushort correctFooterFlag = 0x5555;

		public PLCConnection(string portName, int baudRate)
		{
			connection = new SerialPort(portName, baudRate);
			connection.Open();
		}

		~PLCConnection()
		{
			connection.Close();
		}

		public override void ProvideData()
		{
			byte[] headerData = new byte[6];

			ushort headerFlag;
			ushort comId;
			short id;
			ushort payloadSize;
			byte[] payload;

			byte[] footerData = new byte[2];
			int footerFlag;

			while (connection.BytesToRead > 8)
			{
				connection.Read(headerData, 0, 6);

				headerFlag = BitConverter.ToUInt16(headerData, 0);

				if (headerFlag == correctHeaderFlag)
				{
					payloadSize = (ushort)headerData[2];
					comId = (ushort)headerData[3];
					id = BitConverter.ToInt16(headerData, 4);

					payload = new byte[payloadSize];

					connection.Read(payload, 0, payloadSize);
					connection.Read(footerData, 0, 2);

					footerFlag = BitConverter.ToUInt16(footerData, 0);

					if (footerFlag == correctFooterFlag)
					{
						AddData(new RawData(DateTime.Now, comId, id, payload));
					}
					else
					{
						connection.DiscardInBuffer();
					}
				}
				else
				{
					connection.DiscardInBuffer();
				}
			}
		}

		private void AddData(RawData entity)
		{
			foreach (DataStorage<RawData> dataStorage in dataStoragesOutput)
			{
				dataStorage.Add(entity);
			}
		}
	}
}
