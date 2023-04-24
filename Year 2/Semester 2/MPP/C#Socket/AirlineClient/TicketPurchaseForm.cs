
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AirlineClient
{
    public partial class TicketPurchaseForm : Form
    {

        private AirlineClientController controller;
        private int id_flight;
        public TicketPurchaseForm(AirlineClientController controller, int id_flight)
        {
            InitializeComponent();
            this.id_flight = id_flight;
            this.controller = controller;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string client_name=clientNameTextBox.Text;
            string address=addressTextBox.Text;
            if (client_name=="" || address=="")
            {
                MessageBox.Show("Please fill all fields!");
            }
            else
            {
                controller.Service.buyTicket(id_flight, client_name, address);
            }
        }

        private void TicketPurchaseForm_Load(object sender, EventArgs e)
        {

        }
    }
}
