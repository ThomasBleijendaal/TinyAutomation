using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using SCADA.Data;
using SCADA.Data.Types;
using SCADA.Threading;
using SCADA.RemoteObjects;

namespace SCADA
{
	class Program
	{
		static public PLC RedBoard;
		
		static void Main(string[] args)
		{
			DataStorage<RawData> rawDataUpload = new DataStorage<RawData>();
		
			RedBoard = new PLC(2, "COM3", 115200);

			RedBoard.Provider.AttachDataOutput(rawDataUpload);

			DummyConsumer dummy = new DummyConsumer();

			dummy.AttachDataInput(rawDataUpload);

			DataThread thread = new DataThread();

			thread.AttachProvider(RedBoard.Provider);
			thread.AttachConsumer(dummy);

			thread.Start();
		}
	}

	class DummyConsumer : DataConsumer<RawData>
	{
		public override void ConsumeData()
		{
			for (int i = 0; i < DataStoragesInput.Count; i++)
			{
				DataResult<RawData> result = DataStoragesInput[i].Get(ConsumedDate[i]);
				if (result.Entities.Count > 0)
				{
					foreach (RawData entity in result.Entities)
					{
						Console.WriteLine(entity.ToString());
					}
					ConsumedDate[i] = result.EndTimeStamp;
				}
			}
		}
	}
}
