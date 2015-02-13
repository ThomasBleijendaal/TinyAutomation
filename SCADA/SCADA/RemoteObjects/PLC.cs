using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using SCADA.Data;
using SCADA.Data.Types;

namespace SCADA.RemoteObjects
{
	partial class PLC
	{
		public PLCDataProvider Provider;
		public DataStorage<CommunicationData> DataIn;
		public DataStorage<RemoteSubscriberData> RemoteSubscribers;
		public PLCDataConsumer Consumer;

		private PLCConnection Connection;

		public const byte CommunicationHeaderFlag = 0xAA;
		public const byte RemoteSubscriberHeaderFlag = 0xBB;
		public const byte FooterFlag = 0x55;

		public byte Address;

		public PLC(byte address, string portName, int baudRate)
		{
			Address = address;
			Connection = new PLCConnection(portName, baudRate);

			Provider = new PLCDataProvider(this);

			DataIn = new DataStorage<CommunicationData>();
			RemoteSubscribers = new DataStorage<RemoteSubscriberData>();

			Consumer = new PLCDataConsumer(this);
			Consumer.AttachStorageSource(DataIn);

		}
	}
}
