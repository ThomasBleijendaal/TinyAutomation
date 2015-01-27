using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataProvider<T> : IDataProvider where T : IDataEntry
	{
		protected List<DataStorage<T>> Destinations = new List<DataStorage<T>>();

		public void AttachStorageDestination(DataStorage<T> dataStorage)
		{
			Destinations.Add(dataStorage);
		}

		public abstract void ProvideData();
	}
}
