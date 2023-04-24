using log4net;
using Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Networking.utils
{
    public class RpcConcurrentServer : AbsConcurrentServer
    {
        private readonly IService service;
        private static readonly ILog logger = LogManager.GetLogger("RpcConcurrentServer");

        private ClientWorker worker;
        public RpcConcurrentServer(string host, int port, IService service) : base(host, port)
        {
            this.service = service;
            logger.Info("RpcConcurrentServer created");
            Console.WriteLine(@"RpcConcurrentServer created");
        }
        protected override Thread CreateWorker(TcpClient client)
        {
            worker = new ClientWorker(service, client);
            return new Thread(new ThreadStart(worker.Run));
        }

    }
}
