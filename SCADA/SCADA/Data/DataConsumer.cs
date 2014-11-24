using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataConsumer<T> : IDataConsumer where T : IDataEntity
	{
		protected List<DataStorage<T>> dataStoragesInput = new List<DataStorage<T>>();
		protected List<DateTime> consumedDate = new List<DateTime>();

		public void AttachDataInput(DataStorage<T> dataStorage)
		{
			dataStoragesInput.Add(dataStorage);
			consumedDate.Add(DateTime.MinValue);
		}

		public abstract void ConsumeData();
	}
}
