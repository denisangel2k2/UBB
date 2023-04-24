using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.Sql;
using System.Data.SQLite;
using System.Data.Common;
using log4net;


namespace Persistency
{
    internal static class DatabaseUtilities
    {
        private static readonly ILog log = LogManager.GetLogger("DatabaseUtilities");
        private static DbConnection con_instance = null;


        public static DbConnection getConnection(IDictionary<string, string> props)
        {

            try
            {
                if (con_instance == null || con_instance.State == System.Data.ConnectionState.Closed)
                {

                    return getNewConnection(props);

                }

            }
            catch (Exception e)
            {
                log.Error(e);
            }

            return con_instance;
        }
        private static DbConnection getNewConnection(IDictionary<string, string> props)
        {
            DbConnection connection = null;
            try
            {
                if (props["ConnectionString_SQLite"] != "")
                    connection = new SQLiteConnection(props["ConnectionString_SQLite"]);
                connection.Open();
            }
            catch (Exception ex)
            {
                log.Error(ex);

            }
            return connection;
        }
    }
}
