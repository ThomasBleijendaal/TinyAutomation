using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	abstract class DataConverter<Tin, Tout> : IDataConverter where Tin : IDataEntity where Tout : IDataEntity
	{
		protected List<DataStorage<Tin>> DataStoragesInput = new List<DataStorage<Tin>>();
		protected List<DataStorage<Tout>> DataStoragesOutput = new List<DataStorage<Tout>>();
		protected List<DateTime> ConsumedDate = new List<DateTime>();

		public void AttachDataInput(DataStorage<Tin> dataStorage)
		{
			DataStoragesInput.Add(dataStorage);
			ConsumedDate.Add(DateTime.MinValue);
		}

		public void AttachDataOutput(DataStorage<Tout> dataStorage)
		{
			DataStoragesOutput.Add(dataStorage);
		}

		public abstract void ConvertData();
	}
}
