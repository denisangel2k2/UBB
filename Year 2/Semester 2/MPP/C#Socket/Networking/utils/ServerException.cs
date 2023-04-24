using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.utils
{
    public class ServerException : Exception
    {
        public ServerException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
