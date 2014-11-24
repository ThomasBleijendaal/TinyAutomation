using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SCADA.Data;
using SCADA.Data.Types;

namespace SCADA
{
	class RawDataConverter : DataConverter<RawData, ObjectData>
	{
		public override void ConvertData()
		{
			for (int i = 0; i < DataStoragesInput.Count; i++)
			{
				DataResult<RawData> result = DataStoragesInput[i].Get(ConsumedDate[i]);
				if (result.Entities.Count > 0)
				{
					foreach (RawData entity in result.Entities)
					{
						IObjectData obj = ObjectData.GetTypical(entity.Data().ComId);
					}
					ConsumedDate[i] = result.EndTimeStamp;
				}
			}
		}
	}
}
