namespace MusicalLab2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            parentProdCoardeGridView = new DataGridView();
            childCoardeGridView = new DataGridView();
            deleteButton = new Button();
            addButton = new Button();
            refreshButton = new Button();
            label1 = new Label();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)parentProdCoardeGridView).BeginInit();
            ((System.ComponentModel.ISupportInitialize)childCoardeGridView).BeginInit();
            SuspendLayout();
            // 
            // parentProdCoardeGridView
            // 
            parentProdCoardeGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            parentProdCoardeGridView.Location = new Point(18, 52);
            parentProdCoardeGridView.Margin = new Padding(2);
            parentProdCoardeGridView.Name = "parentProdCoardeGridView";
            parentProdCoardeGridView.RowHeadersWidth = 72;
            parentProdCoardeGridView.RowTemplate.Height = 37;
            parentProdCoardeGridView.Size = new Size(496, 226);
            parentProdCoardeGridView.TabIndex = 0;
            // 
            // childCoardeGridView
            // 
            childCoardeGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            childCoardeGridView.Location = new Point(18, 321);
            childCoardeGridView.Margin = new Padding(2);
            childCoardeGridView.Name = "childCoardeGridView";
            childCoardeGridView.RowHeadersWidth = 72;
            childCoardeGridView.RowTemplate.Height = 37;
            childCoardeGridView.Size = new Size(496, 251);
            childCoardeGridView.TabIndex = 1;
            childCoardeGridView.CellValueChanged += childCoardeGridView_CellValueChanged;
            // 
            // deleteButton
            // 
            deleteButton.Location = new Point(112, 587);
            deleteButton.Margin = new Padding(2);
            deleteButton.Name = "deleteButton";
            deleteButton.Size = new Size(89, 36);
            deleteButton.TabIndex = 2;
            deleteButton.Text = "Delete";
            deleteButton.UseVisualStyleBackColor = true;
            deleteButton.Click += deleteButton_Click;
            // 
            // addButton
            // 
            addButton.Location = new Point(18, 587);
            addButton.Name = "addButton";
            addButton.Size = new Size(89, 36);
            addButton.TabIndex = 3;
            addButton.Text = "Add";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // refreshButton
            // 
            refreshButton.Location = new Point(439, 587);
            refreshButton.Name = "refreshButton";
            refreshButton.Size = new Size(75, 36);
            refreshButton.TabIndex = 4;
            refreshButton.Text = "Refresh";
            refreshButton.UseVisualStyleBackColor = true;
            refreshButton.Click += refreshButton_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(176, 19);
            label1.Name = "label1";
            label1.Size = new Size(158, 21);
            label1.TabIndex = 5;
            label1.Text = "Producatori Coarde";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label2.Location = new Point(234, 290);
            label2.Name = "label2";
            label2.Size = new Size(64, 21);
            label2.TabIndex = 6;
            label2.Text = "Coarde";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(538, 659);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(refreshButton);
            Controls.Add(addButton);
            Controls.Add(deleteButton);
            Controls.Add(childCoardeGridView);
            Controls.Add(parentProdCoardeGridView);
            Margin = new Padding(2);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)parentProdCoardeGridView).EndInit();
            ((System.ComponentModel.ISupportInitialize)childCoardeGridView).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView parentProdCoardeGridView;
        private DataGridView childCoardeGridView;
        private Button deleteButton;
        private Button addButton;
        private Button refreshButton;
        private Label label1;
        private Label label2;
    }
}