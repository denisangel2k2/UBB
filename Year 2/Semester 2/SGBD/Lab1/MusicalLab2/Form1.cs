using Microsoft.Data.SqlClient;
using System.Data;

namespace MusicalLab2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

        }
        private SqlConnection connection = null;
        private SqlDataAdapter coardeAdapter = new SqlDataAdapter();
        private SqlDataAdapter prodCoardeAdapter = new SqlDataAdapter();
        private DataSet dataSet = new DataSet();
        //private DataSet dataSetCoarde;
        private SqlCommandBuilder cmbl;
        private BindingSource parentBS = new BindingSource();
        private BindingSource childBS = new BindingSource();

        private string connectionString = @"Server=LAPTOP-RI290K7P\SQLEXPRESS;Database=MusicDatabase;
        Integrated Security=true;TrustServerCertificate=true;";

        private void loadTables()
        {
            try
            {
                using (connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    coardeAdapter.SelectCommand = new SqlCommand("SELECT id_coarda, nume_material,vechime,refolosit,id_prod,C.id_material_coarda FROM Coarde C INNER JOIN MaterialeCoarde M on M.id_material_coarda=C.id_material_coarda;", connection);
                    //coardeAdapter.SelectCommand = new SqlCommand("SELECT id_coarda, id_material_coarda,vechime,refolosit FROM Coarde;", connection);
                    prodCoardeAdapter.SelectCommand = new SqlCommand("SELECT * FROM ProducatoriCoarde;", connection);

                    if (dataSet.Tables.Contains("Coarde"))
                        dataSet.Tables["Coarde"].Clear();


                    if (dataSet.Tables.Contains("ProducatoriCoarde"))
                        dataSet.Tables["ProducatoriCoarde"].Clear();


                    prodCoardeAdapter.Fill(dataSet, "ProducatoriCoarde");
                    coardeAdapter.Fill(dataSet, "Coarde");


                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void bindParentToChild(DataSet dataSet)
        {
            parentBS.DataSource = dataSet.Tables["ProducatoriCoarde"];
            parentProdCoardeGridView.DataSource = parentBS;
            DataColumn parentColumn = dataSet.Tables["ProducatoriCoarde"].Columns["id_prod"];
            DataColumn childColumn = dataSet.Tables["Coarde"].Columns["id_prod"];
            DataRelation relation = new DataRelation("FK_ProdCoarde", parentColumn, childColumn);
            dataSet.Relations.Add(relation);
            childBS.DataSource = parentBS;
            childBS.DataMember = "FK_ProdCoarde";
            childCoardeGridView.DataSource = childBS;

        }
        private void openNewForm()
        {
            try
            {
                int id = Convert.ToInt32(parentProdCoardeGridView.CurrentRow.Cells[0].Value);

                Form2 form2 = new Form2(id);
                form2.ShowDialog();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            loadTables();
            bindParentToChild(dataSet);
        }

        private void childCoardeGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                using (connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    string updateQuery = "UPDATE Coarde SET vechime = @vechime, refolosit=@refolosit, id_material_coarda=@idmat WHERE id_coarda = @id";
                    DataGridViewRow row = childCoardeGridView.Rows[e.RowIndex];


                    string id = row.Cells[0].Value.ToString();
                    string idmat = row.Cells[5].Value.ToString();
                    //string mat = row.Cells[2].Value.ToString();
                    string vechime = row.Cells[2].Value.ToString();
                    bool refolosit = Convert.ToBoolean(row.Cells[3].Value.ToString());
                    //string id_prod = row.Cells[4].Value.ToString();
                    SqlCommand command = new SqlCommand(updateQuery, connection);
                    //command.Parameters.AddWithValue("@mat", mat);
                    command.Parameters.AddWithValue("@vechime", vechime);
                    command.Parameters.AddWithValue("@refolosit", refolosit);
                    command.Parameters.AddWithValue("@id", id);
                    command.Parameters.AddWithValue("@idmat", idmat);
                    command.ExecuteNonQuery();

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);

            }
            loadTables();
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            try
            {
                string deltesql = "DELETE FROM Coarde where id_coarda=@id";
                using (connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    try
                    {
                        int id = Convert.ToInt32(childCoardeGridView.CurrentRow.Cells[0].Value);
                        SqlCommand command = new SqlCommand(deltesql, connection);
                        command.Parameters.AddWithValue("@id", id);
                        command.ExecuteNonQuery();

                        loadTables();
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Cannot delete");
                    }

                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void parentProdCoardeGridView_Click(object sender, EventArgs e)
        {
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            openNewForm();
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            loadTables();
        }
    }
}