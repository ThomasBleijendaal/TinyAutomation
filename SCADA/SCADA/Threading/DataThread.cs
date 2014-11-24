using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using SCADA.Data;

namespace SCADA.Threading
{
	class DataThread: IDataThread
	{
		private List<IDataProvider> providers = new List<IDataProvider>();
		private List<IDataConverter> converters = new List<IDataConverter>();
		private List<IDataConsumer> consumers = new List<IDataConsumer>();
		
		private Thread hostThread;

		public DataThread()
		{
			hostThread = new Thread(new ThreadStart(Run));
		}

		public void Start()
		{
			hostThread.Start();
		}

		private void Run()
		{
			while (true)
			{
				foreach (IDataProvider provider in providers)
				{
					provider.ProvideData();
				}

				foreach(IDataConsumer consumer in consumers)
				{
					consumer.ConsumeData();
				}

				Thread.Sleep(1);
			}
		}

		public void AttachProvider(IDataProvider provider)
		{
			providers.Add(provider);
		}

		public void AttachConverter(IDataConverter converter)
		{
			converters.Add(converter);
		}

		public void AttachConsumer(IDataConsumer consumer)
		{
			consumers.Add(consumer);
		}
	}
}
