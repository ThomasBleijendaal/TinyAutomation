using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataConverter<Tin, Tout> : IDataConverter where Tin : IDataEntity where Tout : IDataEntity
	{
		protected List<DataStorage<Tin>> dataStoragesInput = new List<DataStorage<Tin>>();
		protected List<DataStorage<Tout>> dataStoragesOutput = new List<DataStorage<Tout>>();
		protected List<DateTime> consumedDate = new List<DateTime>();

		public void AttachDataInput(DataStorage<Tin> dataStorage)
		{
			dataStoragesInput.Add(dataStorage);
			consumedDate.Add(DateTime.MinValue);
		}

		public void AttachDataOutput(DataStorage<Tout> dataStorage)
		{
			dataStoragesOutput.Add(dataStorage);
		}

		public abstract void ConvertData();
	}
}
