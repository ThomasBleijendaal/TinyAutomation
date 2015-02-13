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
			communication = new Communication(0x01);
			communication.Add(new PLC(0xA0, "COM3", 115200));
			communication.Add(new PLC(0XA1, "COM5", 115200));

			if (communication.Init())
			{
				communication.Start();
			}

			DummyConsumer dummy = new DummyConsumer();
			dummy.AttachStorageSource(communication.Data);

			DataThread thread = new DataThread();

			thread.AttachConsumer(dummy);

			thread.Start();
		}
	}

	class DummyConsumer : DataConsumer<CommunicationData>
	{
		public override bool ConsumeEntry(CommunicationData entry)
		{
			Console.WriteLine("DummyConsumer: {0} {1} {2} {3} {4}", entry.SourceAddress, entry.DestinationAddress, entry.ComId, entry.Id, entry.Data.Length);

			return true;
		}
	}
}
