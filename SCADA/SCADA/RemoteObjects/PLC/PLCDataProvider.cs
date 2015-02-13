using System;

using SCADA.Data;
using SCADA.Data.Types;

namespace SCADA.RemoteObjects
{
	partial class PLC
	{
		public class PLCDataProvider : DataProvider<CommunicationData>
		{
			private PLC Parent;

			public PLCDataProvider(PLC parent)
			{
				Parent = parent;
			}

			public override void ProvideData()
			{
				while (Parent.Connection.CanRead())
				{
					switch (Parent.Connection.ReadByte())
					{
						case PLC.CommunicationHeaderFlag:
							ReadCommuncationData();
							break;

						case PLC.RemoteSubscriberHeaderFlag:
							ReadRemoteSubscriberData();
							break;
					}
				}
			}

			private void ReadCommuncationData()
			{
				byte[] headerData = new byte[8];

				byte sourceAddress;
				byte destinationAddress;
				ushort payloadSize;
				ushort comId;
				short id;

				byte[] payload;

				byte footerFlag;

				headerData = Parent.Connection.ReadBytes(8);

				sourceAddress = headerData[0];
				destinationAddress = headerData[1];
				payloadSize = (ushort)(headerData[3] << 8 | headerData[2]);
				comId = (ushort)(headerData[5] << 8 | headerData[4]);
				id = (short)(headerData[7] << 8 | headerData[6]);

				payload = Parent.Connection.ReadBytes(payloadSize);

				footerFlag = Parent.Connection.ReadByte();

				if (footerFlag == PLC.FooterFlag)
				{
					AddData(new CommunicationData(sourceAddress, destinationAddress, comId, id, payload));
				}
			}

			private void ReadRemoteSubscriberData()
			{
				byte[] payload;

				short communicationId;
				byte sourceAddress;
				ushort comId;
				short id;
				byte footerFlag;

				payload = Parent.Connection.ReadBytes(7);

				footerFlag = Parent.Connection.ReadByte();

				if (footerFlag == PLC.FooterFlag)
				{
					communicationId = (short)(payload[0] << 8 | payload[1]);
					sourceAddress = payload[2];
					comId = (ushort)(payload[4] << 8 | payload[3]);
					id = (short)(payload[6] << 8 | payload[5]);

					Parent.RemoteSubscribers.Add(new RemoteSubscriberData(communicationId, sourceAddress, Parent.Address, comId, id));
				}
			}
		}
	}
}
