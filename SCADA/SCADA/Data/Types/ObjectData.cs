// TODO: alleen een data en settings struct maken in PLC en deze beide kanten op kunnen sturen.

using System;

namespace SCADA.Data.Types
{
	class ObjectData<IObjectData> : IDataEntry
	{
		private DateTime _TimeStamp;

		public DateTime TimeStamp() 
		{ 
			return DateTime.Now; 
		}

		public ObjectData(DateTime timeStamp)
		{
			_TimeStamp = timeStamp;
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
