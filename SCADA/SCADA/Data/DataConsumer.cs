using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataConsumer<T> : IDataConsumer where T : IDataEntry
	{
		protected List<DataStorage<T>> Sources = new List<DataStorage<T>>();
		protected List<DateTime> ConsumedDate = new List<DateTime>();

		public void AttachStorageSource(DataStorage<T> dataStorage)
		{
			Sources.Add(dataStorage);
			ConsumedDate.Add(DateTime.MinValue);
		}

		public void ConsumeData()
		{
			for (int i = 0; i < Sources.Count; i++)
			{
				DataResult<T> result = Sources[i].Get(ConsumedDate[i]);
				{
					if (result.Entries.Count > 0)
					{
						foreach (T entry in result.Entries)
						{
							if (!ConsumeEntry(entry))
							{
								throw new Exception("No consumption of entry");
							}
						}
						ConsumedDate[i] = result.EndTimeStamp;
					}
				}
			}
		}

		public abstract bool ConsumeEntry(T entry);
	}
}
