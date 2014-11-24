using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCADA.Data
{
	class DataResult<T>
	{
		public DateTime StartTimeStamp = DateTime.MinValue;
		public DateTime EndTimeStamp = DateTime.MinValue;

		public List<T> Entities = new List<T>();
	}
}
