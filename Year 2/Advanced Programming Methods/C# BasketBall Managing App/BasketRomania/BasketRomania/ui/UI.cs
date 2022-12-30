using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BasketRomania.service;
namespace BasketRomania.ui
{
    internal class UI<ID>
    {
        private Service<ID> service;
        public UI(Service<ID> service)
        {
            this.service = service;
            run();
        }
        private void run()
        {

            ArrayList filepath_lista = service.testFunction();
            foreach (string filepath in filepath_lista)
            {
                Console.WriteLine(filepath);
            }
        }
    }
}
