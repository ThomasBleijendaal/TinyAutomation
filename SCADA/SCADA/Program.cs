using System;
using System.IO;
using System.IO.Ports;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using SCADA.Data;
using SCADA.Data.Types;
using SCADA.Threading;

namespace SCADA
{
	class Program
	{
		
		static void Main(string[] args)
		{
			DataStorage<RawData> rawDataUpload = new DataStorage<RawData>();
		
			PLCConnection arduinoConnection = new PLCConnection("COM3", 115200);

			DummyConsumer dummy = new DummyConsumer();

			arduinoConnection.AttachDataOutput(rawDataUpload);

			dummy.AttachDataInput(rawDataUpload);

			DataThread thread = new DataThread();

			thread.AttachProvider(arduinoConnection);
			thread.AttachConsumer(dummy);

			thread.Start();
		}
	}

	class DummyConsumer : DataConsumer<RawData>
	{
		public override void ConsumeData()
		{
			for (int i = 0; i < dataStoragesInput.Count; i++)
			{
				DataResult<RawData> result = dataStoragesInput[i].Get(consumedDate[i]);
				if (result.Entities.Count > 0)
				{
					foreach (RawData entity in result.Entities)
					{
						Console.WriteLine(entity.ToString());
					}
					consumedDate[i] = result.EndTimeStamp;
				}
			}
		}
	}
}
