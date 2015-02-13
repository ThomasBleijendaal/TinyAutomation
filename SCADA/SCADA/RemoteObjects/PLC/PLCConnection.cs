using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SCADA.RemoteObjects
{
	partial class PLC
	{		
		private class PLCConnection
		{
			private SerialPort Connection;

			public bool IsOpen;
			private bool Started;

			private Queue<byte> buffer;

			public PLCConnection(string portName, int baudRate)
			{
				IsOpen = false;
				Started = false;

				buffer = new Queue<byte>(4096);
				buffer.Clear();

				try
				{
					Connection = new SerialPort(portName, baudRate,Parity.None, 8, StopBits.One);
					Connection.DtrEnable = true;
					Connection.RtsEnable = true;
					Connection.WriteTimeout = 500;
					Connection.Open();
				}
				catch (Exception e)
				{
					Console.WriteLine(e.Message);
				}

			}
			~PLCConnection()
			{
				Connection.Close();
			}

			public bool CanRead()
			{
				if (IsOpen)
				{
					return buffer.Count > 0;
				}
				else
				{
					TryOpen();

					if (Started)
					{
						IsOpen = true;
					}

					return false;
				}
			}

			public byte ReadByte()
			{
				if (buffer.Count > 0)
				{
					return buffer.Dequeue();
				}
				else
				{
					return 0x00;
				}
			}

			public byte[] ReadBytes(int byteCount)
			{
				byte[] result = new byte[byteCount];
				int i = -1;

				if (buffer.Count > byteCount)
				{
					while (++i < byteCount)
					{
						result[i] = buffer.Dequeue();
					}
				}
				
				return result;
			}

			public void WriteBytes(byte[] data)
			{
				Console.WriteLine("Writing to " + Connection.PortName);
				try
				{
					Connection.Write(data, 0, data.Length);
					Connection.DiscardOutBuffer();
				}
				catch (Exception) { }
			}

			private void Connection_DataReceived(object sender, SerialDataReceivedEventArgs e)
			{
				while (Connection.BytesToRead > 0)
				{
					buffer.Enqueue((byte)Connection.ReadByte());
				}

				Connection.DiscardInBuffer();
			}

			public void TryOpen()
			{
				byte[] data = new byte[1];
				data[0] = 0xAA;

				while (!Started)
				{
					Connection.Write(data, 0, 1);

					Thread.Sleep(1);

					while (!Started && Connection.BytesToRead > 0)
					{
						Started = Connection.ReadByte() == data[0] || Started;
					}
				}

				// assign event hander to recieve every bit
				Connection.DataReceived += new SerialDataReceivedEventHandler(Connection_DataReceived);
			}
		}
	}
}
