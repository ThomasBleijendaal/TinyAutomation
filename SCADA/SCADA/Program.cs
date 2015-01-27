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
		static public Communication communication;
		
		static void Main(string[] args)
		{
			communication = new Communication(1);
			communication.Add(new PLC(2, "COM3", 115200));

			if (communication.Init())
			{
				communication.Start();
			}

			DummyConsumer dummy = new DummyConsumer();
			dummy.AttachStorageSource(communication.Data);

			DataThread thread = new DataThread();

			thread.AttachConsumer(dummy);

			thread.Start();

		/*	DataStorage<RawData> rawDataUpload = new DataStorage<RawData>();
		
			RedBoard = new PLC(2, "COM3", 115200);

			RedBoard.Provider.AttachDataOutput(rawDataUpload);

			DummyConsumer dummy = new DummyConsumer();

			dummy.AttachDataInput(rawDataUpload);

			DataThread thread = new DataThread();

			thread.AttachProvider(RedBoard.Provider);
			thread.AttachConsumer(dummy);

			thread.Start();*/
		}
	}

	class DummyConsumer : DataConsumer<CommunicationData>
	{
		public override bool ConsumeEntry(CommunicationData entry)
		{
			Console.WriteLine(entry.Data.ToString());

			return true;
		}
	}
}
