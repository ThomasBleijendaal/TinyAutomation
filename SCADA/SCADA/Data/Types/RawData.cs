using System;

namespace SCADA.Data.Types
{
	class RawData : DataEntity<RawDataEntry>
	{
		public override RawData(DateTime timestamp, ushort comId, short id, byte[] data) 
			: base(timestamp, new RawDataEntry(comId, id, data))
		{
			
		}

		public override string ToString()
		{
			return TimeStamp().ToString() + "  " + this.Data().ComId + " " + this.Data().Id + " ";
		}
	}

	class RawDataEntry
	{
		public ushort ComId;
		public short Id;
		public byte[] Data;

		public RawDataEntry(ushort comId, short id, byte[] data)
		{
			ComId = comId;
			Id = id;
			Data = data;
		}
	}
}
