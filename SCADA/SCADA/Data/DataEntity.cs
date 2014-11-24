using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	class DataEntity<T>: IDataEntity
	{
		protected DateTime _TimeStamp;

		protected T _Data;

		public DataEntity(DateTime timestamp, T data)
		{
			this._TimeStamp = timestamp;
			this._Data = data;
		}

		public T Data()
		{
			return this._Data;
		}

		public DateTime TimeStamp()
		{
			return this._TimeStamp;
		}	
	}
}
