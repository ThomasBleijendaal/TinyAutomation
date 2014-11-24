using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataConsumer<T> : IDataConsumer where T : IDataEntity
	{
		protected List<DataStorage<T>> DataStoragesInput = new List<DataStorage<T>>();
		protected List<DateTime> ConsumedDate = new List<DateTime>();

		public void AttachDataInput(DataStorage<T> dataStorage)
		{
			DataStoragesInput.Add(dataStorage);
			ConsumedDate.Add(DateTime.MinValue);
		}

		public abstract void ConsumeData();
	}
}
