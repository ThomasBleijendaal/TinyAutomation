using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataConverter<SourceEntry, DestinationEntry> : IDataConverter 
		where SourceEntry : IDataEntry
		where DestinationEntry : IDataEntry
	{
		protected List<DataStorage<SourceEntry>> Sources = new List<DataStorage<SourceEntry>>();
		protected List<DataStorage<DestinationEntry>> Destinations = new List<DataStorage<DestinationEntry>>();
		protected List<DateTime> ConsumedDate = new List<DateTime>();

		public void AttachStorageSource(DataStorage<SourceEntry> dataStorage)
		{
			Sources.Add(dataStorage);
			ConsumedDate.Add(DateTime.MinValue);
		}

		public void AttachStorageDestination(DataStorage<DestinationEntry> dataStorage)
		{
			Destinations.Add(dataStorage);
		}

		public void ConvertData()
		{
			for (int i = 0; i < Sources.Count; i++)
			{
				DataResult<SourceEntry> result = Sources[i].Get(ConsumedDate[i]);
				{
					if (result.Entries.Count > 0)
					{
						foreach (SourceEntry entry in result.Entries)
						{
							if (!ConvertEntry(entry))
							{
								throw new Exception("No conversion of entry");
							}
						}
						ConsumedDate[i] = result.EndTimeStamp;
					}
				}
			}
		}

		public abstract bool ConvertEntry(SourceEntry entry);
	}
}
