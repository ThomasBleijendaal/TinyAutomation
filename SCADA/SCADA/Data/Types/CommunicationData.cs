using System;

namespace SCADA.Data.Types
{
	class CommunicationData : IDataEntry
	{
		private DateTime _TimeStamp;
		public byte SourceAddress;
		public byte DestinationAddress;
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

		public CommunicationData(byte sourceAddress, byte destinationAddress, ushort comId, short id, byte[] data)
		{
			_TimeStamp = DateTime.Now;

			SourceAddress = sourceAddress;
			DestinationAddress = destinationAddress;
			ComId = comId;
			Id = id;
			Data = data;
		}

		public void ConvertFrom(IDataEntry entry)
		{
			throw new InvalidCastException();
		}

		public static CommunicationData CreateFromRawData(byte[] data)
		{
			CommunicationData entry = new CommunicationData();



			return entry;
		}

		public byte[] ConvertToRawData()
		{
			
			byte[] headerData = new byte[9];
			byte[] payload = Data;
			byte[] footerData = new byte[1];

			headerData[0] = (byte)0xAA;
			headerData[1] = (byte)0xFF;
			headerData[2] = (byte)0xFF;
			headerData[3] = 0; // (byte)((Data.Length & 0xFF00) >> 8);
			headerData[4] = 9; // (byte)(Data.Length & 0x00FF);
			headerData[5] = 0; // (byte)((ComId & 0xFF00) >> 8);
			headerData[6] = 8; // (byte)(ComId & 0x00FF);
			headerData[7] = 0; // (byte)((Id & 0xFF00) >> 8);
			headerData[8] = 0; // (byte)(Id & 0x00FF);

			footerData[0] = (byte)0x55;

			byte[] result = new byte[10 + Data.Length];

			headerData.CopyTo(result, 0);
			payload.CopyTo(result, 9);
			footerData.CopyTo(result, 9 + Data.Length);

			return result;
		}
	}
}
