
using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace AirlineClient
{
   public partial class MainForm : Form
    {
        
        private readonly AirlineClientController controller;

        public MainForm(AirlineClientController controller)
        {
            InitializeComponent();
            this.controller=controller;
            initLists();
            controller.UpdateEvent += UserUpdate;

        }

        private List<Flight> allFlights;
        private List<Flight> filteredFlights;

        private delegate void UpdateListBoxCallback(DataGridView list, IList<Flight> data);
        private static void UpdateListBox(DataGridView gridView, IList<Flight> newData)
        {
            gridView.DataSource = null;
            gridView.DataSource = newData;
            gridView.Columns["Id"].Visible = false;
        }
        private void UserUpdate(object sender, EmployeeEventArgs e)
        {
            if (e.EmployeeEventType != EmployeeEvent.BUY_TICKET) return;
            var ticket = (Ticket)e.Data;

            
            foreach(var flight in allFlights)
            {
                if (flight.Id!=ticket.FlightId) continue;
                flight.AvailableSeats--;
            }

            allFlightsGridView.BeginInvoke(new UpdateListBoxCallback(UpdateListBox),
                new Object[] { allFlightsGridView, allFlights });
            
            foreach(var flight in filteredFlights)
            {
                if (flight.Id!=ticket.FlightId) continue;
                flight.AvailableSeats--;
            }

            filteredFlightsGridView.BeginInvoke(new UpdateListBoxCallback(UpdateListBox),
                new Object[] { filteredFlightsGridView, filteredFlights });
            

        }
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            controller.logout();
            controller.UpdateEvent -= UserUpdate;
        }
        
        private void initLists()
        {
            allFlights = controller.Service.getAllFlights().ToList();
            allFlightsGridView.DataSource = allFlights;
            allFlightsGridView.Columns["Id"].Visible = false;
            filteredFlightsGridView.DataSource = filteredFlights;


            

        }
        private void Form2_Load(object sender, EventArgs e)
        {
            //initLists();
            dateTimePicker1.Format=DateTimePickerFormat.Custom;
            dateTimePicker1.CustomFormat="dd.MM.yyyy";
            loggedUserLabel.Text="Logged as "+controller.LoggedEmployee.Username;
        }

        private void allFlightsGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            /*
            if (e.ColumnIndex == allFlightsGridView.Columns["availableSeats"].Index && e.RowIndex >= 0)
            {
                Flight flight = allFlightsGridView.Rows[e.RowIndex].DataBoundItem as Flight;
                if (flight != null)
                {
                    e.Value = flight.NumberOfSeats - controller.Service.getNumberOfTicketsForFlights(flight.Id);
                }
            }
            */
        }

        private void filteredFlightsGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            /*
            if (e.ColumnIndex == filteredFlightsGridView.Columns["availableSeats"].Index && e.RowIndex >= 0)
            {
                Flight flight = filteredFlightsGridView.Rows[e.RowIndex].DataBoundItem as Flight;
                if (flight != null)
                {
                    e.Value = flight.NumberOfSeats - controller.Service.getNumberOfTicketsForFlights(flight.Id);
                }
            }
            */
        }
        

        private void searchButton_Click(object sender, EventArgs e)
        {
            string destination = destinationTextBox.Text;
            string date = dateTimePicker1.Text;
            filteredFlights = controller.Service.getFlights(destination,date).ToList();
            filteredFlightsGridView.DataSource = filteredFlights;
            filteredFlightsGridView.Columns["Id"].Visible = false;

            //if (filteredFlightsGridView.Columns["availableSeats"]==null)
            //    filteredFlightsGridView.Columns.Add("availableSeats", "Available seats");
        }

        private void logoutButton_Click(object sender, EventArgs e)
        {
            this.Hide();
            controller.logout();
            controller.UpdateEvent -= UserUpdate;
            LoginForm loginForm = new LoginForm(new AirlineClientController(controller.Service));         
            loginForm.ShowDialog();
            this.Close();
        }

        private void filteredFlightsGridView_Click(object sender, EventArgs e)
        {
            if (filteredFlightsGridView.CurrentCell != null){
                int rowIndex = filteredFlightsGridView.CurrentCell.RowIndex;
                Flight selected_flight = filteredFlightsGridView.Rows[rowIndex].DataBoundItem as Flight;
                if (selected_flight != null)
                {
                    TicketPurchaseForm ticketPurchaseForm = new TicketPurchaseForm(controller, selected_flight.Id);
                    ticketPurchaseForm.ShowDialog();
                }
            }
        }
    }
}
