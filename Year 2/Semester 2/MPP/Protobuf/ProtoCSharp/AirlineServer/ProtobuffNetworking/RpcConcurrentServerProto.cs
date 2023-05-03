
using Services;
using System;

using System.Net.Sockets;

using System.Threading;
using ProtobuffNetworking;

namespace Networking.utils
{
    public class RpcConcurrentServerProto : AbsConcurrentServer
    {
        private readonly IService service;
        
        private ProtoWorker worker;
        public RpcConcurrentServerProto(string host, int port, IService service) : base(host, port)
        {
            this.service = service;
            Console.WriteLine(@"RpcConcurrentServer created");
        }
        protected override Thread CreateWorker(TcpClient client)
        {
            worker = new ProtoWorker(service, client);
            return new Thread(new ThreadStart(worker.Run));
        }

    }
}
