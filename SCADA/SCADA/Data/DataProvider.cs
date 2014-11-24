using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataProvider<T> : IDataProvider where T : IDataEntity
	{
		protected List<DataStorage<T>> dataStoragesOutput = new List<DataStorage<T>>();

		public void AttachDataOutput(DataStorage<T> dataStorage)
		{
			dataStoragesOutput.Add(dataStorage);
		}

		public abstract void ProvideData();
	}
}
