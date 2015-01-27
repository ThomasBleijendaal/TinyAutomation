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

		private CommunicationDispatcher Dispatcher;

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

			//ObjDataOutput = new DataStorage<ObjectData>();

			DataHandlingThread = new DataThread();

			//CommToObj = new DataConverter<CommunicationData, ObjectData>();
			//CommToObj.AttachStorageSource(CommDataInput);
			//CommToObj.AttachStorageDestination(ObjDataInput);

			//DataHandlingThread.AttachConverter(CommToObj);

			DataHandlingThread.AttachConsumer(Dispatcher);
		}

		public bool Init()
		{
			PLCs.ForEach(
				p =>
				{
					p.Provider.AttachStorageDestination(CommDataIn);
					DataHandlingThread.AttachProvider(p.Provider);


				}
			);

			return true;
		}

		public void Start()
		{
			DataHandlingThread.Start();
		}

		public void Add(PLC plc) {
			PLCs.Add(plc);
		}

		private class CommunicationDispatcher : DataConsumer<CommunicationData>
		{
			private Communication Parent;

			public CommunicationDispatcher(Communication parent)
			{
				Parent = parent;
			}

			public override bool ConsumeEntry(CommunicationData entry)
			{
				foreach (PLC plc in Parent.PLCs)
				{
					if(entry.Address == Parent.Address)
					{
						Parent.Data.Add(entry);

						return true;
					}
					else if (entry.Address == plc.Address)
					{
						plc.DataOut.Add(entry);

						return true;
					}
				}

				return false;
			}
		}
	}
}
