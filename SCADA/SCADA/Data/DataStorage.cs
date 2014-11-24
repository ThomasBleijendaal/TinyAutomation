using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	class DataStorage<T> where T : IDataEntity
	{
		public List<T> Entities = new List<T>();

		public void Add(T entity)
		{
			Entities.Add(entity);
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
				foreach (T entity in Entities)
				{
					if (entity.TimeStamp() > startTimeSamp)
					{
						result.Entities.Add(entity);
					}
				}
			}

			if (result.Entities.Count > 0)
			{
				result.StartTimeStamp = result.Entities[0].TimeStamp();
				result.EndTimeStamp = result.Entities.Last().TimeStamp();
			}

			return result;
		}
	}
}
