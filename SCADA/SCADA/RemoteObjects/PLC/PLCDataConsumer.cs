using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SCADA.Data;
using SCADA.Data.Types;

namespace SCADA.RemoteObjects
{
	partial class PLC
	{
		public class PLCDataConsumer : DataConsumer<CommunicationData>
		{
			private PLC Parent;

			public PLCDataConsumer(PLC parent)
			{
				Parent = parent;
			}

			public override bool ConsumeEntry(CommunicationData entry)
			{
				// todo
				Console.WriteLine("Consume " + Parent.Address);

				Parent.Connection.WriteBytes(entry.ConvertToRawData());

				return true;
			}
		}
	}
}
