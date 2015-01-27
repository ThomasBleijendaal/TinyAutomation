using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	class DataStorage<T> where T : IDataEntry
	{
		public List<T> Entries = new List<T>();

		public void Add(T entity)
		{
			Entries.Add(entity);
		}

		public DataResult<T> Get(DateTime start)
		{
			return Get(start, null);
		}
		public DataResult<T> Get(DateTime startTimeSamp, Nullable<TimeSpan> timeSpan)
		{
			DataResult<T> result = new DataResult<T>();

			if (timeSpan == null)
			{
				foreach (T entity in Entries.ToList())
				{
					if (entity.TimeStamp() > startTimeSamp)
					{
						result.Entries.Add(entity);
					}
				}
			}

			if (result.Entries.Count > 0)
			{
				result.StartTimeStamp = result.Entries[0].TimeStamp();
				result.EndTimeStamp = result.Entries.Last().TimeStamp();
			}

			return result;
		}
	}
}
