using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	interface IDataThread
	{
		void AttachProvider(IDataProvider provider);
		void AttachConverter(IDataConverter converter);
		void AttachConsumer(IDataConsumer consumer);
	}
}
