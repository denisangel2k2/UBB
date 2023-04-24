
using Networking;
using Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AirlineClient
{
    internal static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            IService service = new ServiceProxy("127.0.0.1", 55557);
            var controller = new AirlineClientController(service);
            var window = new LoginForm(controller);
            Application.Run(window);
        }
    }
}
