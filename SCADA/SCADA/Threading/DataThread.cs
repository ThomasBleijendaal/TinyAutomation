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
		private List<IDataProvider> Providers = new List<IDataProvider>();
		private List<IDataConverter> Converters = new List<IDataConverter>();
		private List<IDataConsumer> Consumers = new List<IDataConsumer>();
		
		private Thread HostThread;

		public DataThread()
		{
			HostThread = new Thread(new ThreadStart(Run));
		}

		public void Start()
		{
			HostThread.Start();
		}

		private void Run()
		{
			while (true)
			{
				foreach (IDataProvider provider in Providers)
				{
					provider.ProvideData();
				}

				foreach (IDataConverter converter in Converters)
				{
					converter.ConvertData();
				}

				foreach(IDataConsumer consumer in Consumers)
				{
					consumer.ConsumeData();
				}

				Thread.Sleep(100);
			}
		}

		public void AttachProvider(IDataProvider provider)
		{
			Providers.Add(provider);
		}
		public void AttachProvider(List<IDataProvider> providers)
		{
			Providers = Providers.Concat(providers).ToList();
		}

		public void AttachConverter(IDataConverter converter)
		{
			Converters.Add(converter);
		}
		public void AttachConverter(List<IDataConverter> converters)
		{
			Converters = Converters.Concat(converters).ToList();
		}

		public void AttachConsumer(IDataConsumer consumer)
		{
			Consumers.Add(consumer);
		}
		public void AttachConverter(List<IDataConsumer> consumers)
		{
			Consumers = Consumers.Concat(consumers).ToList();
		}
	}
}
