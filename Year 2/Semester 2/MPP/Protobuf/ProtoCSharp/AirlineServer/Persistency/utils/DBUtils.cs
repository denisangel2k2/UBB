using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistency.utils
{
    public static class DBUtils
    {
        private static IDbConnection instance = null;

        public static IDbConnection GetConnection(IDictionary<string, string> props)
        {
            if (instance != null && instance.State != System.Data.ConnectionState.Closed) return instance;
            instance = GetNewConnection(props);
            instance.Open();

            return instance;
        }

        private static IDbConnection GetNewConnection(IDictionary<string, string> props)
        {
            return Persistency.utils.ConnectionFactory.getInstance().createConnection(props);
        }
    }
}
