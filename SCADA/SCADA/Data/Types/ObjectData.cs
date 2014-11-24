using System;

namespace SCADA.Data.Types
{
	class ObjectData : DataEntity<IObjectData>
	{
		public ObjectData(DateTime timestamp, IObjectData data) : base(timestamp, data) 
		{

		}

		public static IObjectData GetTypical(ushort comId)
		{
			switch (comId)
			{
				case 0x00:
				case 0x01:
				case 0x02:
					return new AIObjectData();
				case 0x03:
				case 0x04:
				case 0x05:
					return new AIObjectData();
				case 0x06:
				case 0x07:
				case 0x08:
					return new AIObjectData();
				case 0x09:
				case 0x0A:
				case 0x0B:
					return new AIObjectData();
				case 0xA0:
				case 0xA1:
				case 0xA2:
					return new PIDObjectData();

				default:
					throw new NotSupportedException(comId.ToString());
			}
		}
	}

	interface IObjectData
	{

	}

	class AIObjectData : IObjectData
	{

	}
	class AOObjectData : IObjectData
	{

	}
	class DIObjectData : IObjectData
	{

	}
	class DOObjectData : IObjectData
	{

	}
	class PIDObjectData : IObjectData
	{

	}
}
