using System;

using SCADA.Data;

namespace SCADA.Threading
{
	interface IDataThread
	{
		void AttachProvider(IDataProvider provider);
		void AttachConverter(IDataConverter converter);
		void AttachConsumer(IDataConsumer consumer);
	}
}
