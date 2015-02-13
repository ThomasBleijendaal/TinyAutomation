using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data.Types
{
	class RemoteSubscriberData : IDataEntry
	{
		private DateTime _TimeStamp;
		public short CommunicationId;
		public short SourceAddress;
		public short DestinationAddress;
		public ushort ComId;
		public short Id;

		public DateTime TimeStamp()
		{
			return _TimeStamp;
		}

		public RemoteSubscriberData()
		{
			// do nothing
		}

		public RemoteSubscriberData(short communicationId, short sourceAddress, short destinationAddress, ushort comId, short id)
		{
			_TimeStamp = DateTime.Now;

			CommunicationId = communicationId;
			SourceAddress = sourceAddress;
			DestinationAddress = destinationAddress;
			ComId = comId;
			Id = id;
		}

		public void ConvertFrom(IDataEntry entry)
		{
			throw new InvalidCastException();
		}

		public bool Matches(CommunicationData entry)
		{
			return (entry.SourceAddress == SourceAddress && entry.ComId == ComId && entry.Id == Id);
		}
	}
}
