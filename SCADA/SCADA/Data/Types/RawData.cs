using System;

namespace SCADA.Data.Types
{
	class RawData : DataEntity<RawDataEntry>
	{
		public RawData(DateTime timestamp, byte address, byte remoteAddress, ushort comId, short id, byte[] data) 
			: base(timestamp, new RawDataEntry(address, remoteAddress, comId, id, data))
		{
			
		}

		public override string ToString()
		{
			return TimeStamp().ToString() + "  " + this.Data().ComId + " " + this.Data().Id + " ";
		}
	}

	class RawDataEntry
	{
		public byte Address;
		public byte RemoteAddress;
		public ushort ComId;
		public short Id;
		public byte[] Data;

		public RawDataEntry(byte address, byte remoteAddress, ushort comId, short id, byte[] data)
		{
			Address = address;
			RemoteAddress = remoteAddress;
			ComId = comId;
			Id = id;
			Data = data;
		}
	}
}
