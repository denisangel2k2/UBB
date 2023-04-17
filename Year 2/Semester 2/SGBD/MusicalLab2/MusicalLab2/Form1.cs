using Microsoft.Data.SqlClient;
using System.Configuration;
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
        private SqlDataAdapter childAdapter = new SqlDataAdapter();
        private SqlDataAdapter parentAdapter = new SqlDataAdapter();
        private DataSet dataSet = new DataSet();
        //private DataSet dataSetCoarde;
        private SqlCommandBuilder cmbl;
        private BindingSource parentBS = new BindingSource();
        private BindingSource childBS = new BindingSource();

        private readonly string connectionString = ConfigurationManager.AppSettings["connectionString"];
        private readonly string selectFromParent = ConfigurationManager.AppSettings["selectFromParent"];
        private readonly string selectFromChild = ConfigurationManager.AppSettings["selectFromChild"];
        private readonly string child = ConfigurationManager.AppSettings["child"];
        private readonly string parent = ConfigurationManager.AppSettings["parent"];
        private readonly List<string> paramsForInsert = new List<string>(ConfigurationManager.AppSettings["paramsForInsert"].Split(','));
        private readonly List<string> paramsForDelete = new List<string>(ConfigurationManager.AppSettings["paramsForDelete"].Split(','));
        private readonly List<string> paramsForUpdate = new List<string>(ConfigurationManager.AppSettings["paramsForUpdate"].Split(','));
        private readonly string deleteCommand = ConfigurationManager.AppSettings["deleteCommand"];
        private readonly string updateCommand = ConfigurationManager.AppSettings["updateCommand"];


        private void loadTables()
        {
            try
            {
                using (connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    childAdapter.SelectCommand = new SqlCommand(selectFromChild, connection);
                    //coardeAdapter.SelectCommand = new SqlCommand("SELECT id_coarda, id_material_coarda,vechime,refolosit FROM Coarde;", connection);
                    parentAdapter.SelectCommand = new SqlCommand(selectFromParent, connection);

                    if (dataSet.Tables.Contains(child))
                        dataSet.Tables[child].Clear();


                    if (dataSet.Tables.Contains(parent))
                        dataSet.Tables[parent].Clear();


                    parentAdapter.Fill(dataSet, parent);
                    childAdapter.Fill(dataSet, child);


                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void bindParentToChild(DataSet dataSet)
        {
            parentBS.DataSource = dataSet.Tables[parent];
            parentGridView.DataSource = parentBS;
            DataColumn parentColumn = dataSet.Tables[parent].Columns[paramsForInsert[0].Substring(1)];
            var colname = paramsForDelete[0].Substring(1);
            DataColumn childColumn = dataSet.Tables[child].Columns[paramsForInsert[0].Substring(1)];
            string relationName = "FK_" + parent;
            DataRelation relation = new DataRelation(relationName, parentColumn, childColumn);
            dataSet.Relations.Add(relation);
            childBS.DataSource = parentBS;
            childBS.DataMember = relationName;
            childGridView.DataSource = childBS;

        }
        private void openNewForm()
        {
            try
            {
                int id = Convert.ToInt32(parentGridView.CurrentRow.Cells[0].Value);

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
                    DataGridViewRow row = childGridView.Rows[e.RowIndex];


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
                        int id = Convert.ToInt32(childGridView.CurrentRow.Cells[0].Value);
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