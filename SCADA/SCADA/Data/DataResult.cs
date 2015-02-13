using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	class DataResult<T> where T : IDataEntry
	{
		public DateTime StartTimeStamp = DateTime.MinValue;
		public DateTime EndTimeStamp = DateTime.MinValue;

		public List<T> Entries = new List<T>();

		//public IEnumerable<T> Entries { get; set; }
	}
}
