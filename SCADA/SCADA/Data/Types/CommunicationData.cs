using System;

namespace SCADA.Data.Types
{
	class CommunicationData : IDataEntry
	{
		private DateTime _TimeStamp;
		public byte Address;
		public byte RemoteAddress;
		public ushort ComId;
		public short Id;
		public byte[] Data;
		
		public DateTime TimeStamp()
		{
			return _TimeStamp;
		}

		public CommunicationData()
		{
			// do nothing
		}

		public CommunicationData(DateTime timeStamp, byte address, byte remoteAddress, ushort comId, short id, byte[] data)
		{
			_TimeStamp = timeStamp;
			Address = address;
			RemoteAddress = remoteAddress;
			ComId = comId;
			Id = id;
			Data = data;
		}

		public void ConvertFrom(IDataEntry entry)
		{
			throw new InvalidCastException();
		}
	}
}
