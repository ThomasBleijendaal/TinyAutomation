using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SCADA.Data;
using SCADA.Data.Types;
using SCADA.RemoteObjects;
using SCADA.Threading;

namespace SCADA
{
	class Communication
	{
		private List<PLC> PLCs;

		// plc communication
		public DataStorage<CommunicationData> CommDataIn;

		// local node communication
		public DataStorage<CommunicationData> Data;

		// inter-node communication
		public DataStorage<CommunicationData> NodeDataIn;
		public DataStorage<CommunicationData> NodeDataOut;

		public CommunicationDispatcher Dispatcher;
		public RemoteSubscriberProcessor RemoteSubscriber;

		private List<Type> ObjectDataTypes;
		private List<DataStorage<ObjectData<IObjectData>>> ObjectDataTypesInput;

		private DataThread DataHandlingThread;

		public byte Address;

		public Communication(byte address)
		{
			Address = address;

			PLCs = new List<PLC>();

			Data = new DataStorage<CommunicationData>();
			CommDataIn = new DataStorage<CommunicationData>();

			Dispatcher = new CommunicationDispatcher(this);
			Dispatcher.AttachStorageSource(CommDataIn);

			RemoteSubscriber = new RemoteSubscriberProcessor(this);

			DataHandlingThread = new DataThread();
			DataHandlingThread.AttachConsumer(Dispatcher);
			DataHandlingThread.AttachConsumer(RemoteSubscriber);
		}

		public bool Init()
		{
			foreach (PLC plc in PLCs)
			{
				plc.Provider.AttachStorageDestination(CommDataIn);
				RemoteSubscriber.AttachStorageSource(plc.RemoteSubscribers);

				DataHandlingThread.AttachProvider(plc.Provider);
				DataHandlingThread.AttachConsumer(plc.Consumer);
			};
			
			return true;
		}

		public void Start()
		{
			DataHandlingThread.Start();
		}

		public void Add(PLC plc) {
			PLCs.Add(plc);
		}

		public void AddRemoteSubscriber(RemoteSubscriberData entry)
		{
			Console.WriteLine("Remote Subscriber added!");

			short address = entry.DestinationAddress;

			if (!Dispatcher.ForwardingRules.ContainsKey(address))
			{
				Dispatcher.ForwardingRules.Add(address, new List<RemoteSubscriberData>());
			}

			Dispatcher.ForwardingRules[address].Add(entry);
		}

		public class CommunicationDispatcher : DataConsumer<CommunicationData>
		{
			private Communication Parent;

			public Dictionary<short, List<RemoteSubscriberData>> ForwardingRules;

			public CommunicationDispatcher(Communication parent)
			{
				Parent = parent;
				ForwardingRules = new Dictionary<short, List<RemoteSubscriberData>>();
			}

			public override bool ConsumeEntry(CommunicationData entry)
			{
				bool consumed = false;

				foreach (PLC plc in Parent.PLCs)
				{
					if(entry.DestinationAddress == Parent.Address)
					{
						Parent.Data.Add(entry);

						consumed = true;
					}
					else if (entry.DestinationAddress == plc.Address)
					{
						plc.DataIn.Add(entry);

						consumed = true;
					}

					if (ForwardingRules.ContainsKey(plc.Address)) {
						foreach (RemoteSubscriberData rsdata in ForwardingRules[plc.Address])
						{
							if (rsdata.Matches(entry))
							{
								Console.WriteLine("Duplicating entry");
								plc.DataIn.Add(entry);

								consumed = true;
							}
						}

					}
				}

				return consumed;
			}
		}

		public class RemoteSubscriberProcessor : DataConsumer<RemoteSubscriberData>
		{
			private Communication Parent;

			public RemoteSubscriberProcessor(Communication parent)
			{
				Parent = parent;
			}

			public override bool ConsumeEntry(RemoteSubscriberData entry)
			{
				Console.WriteLine("RemoteSubscriber registered.");
				Parent.AddRemoteSubscriber(entry);

				return false;
			}
		}
	}
}
