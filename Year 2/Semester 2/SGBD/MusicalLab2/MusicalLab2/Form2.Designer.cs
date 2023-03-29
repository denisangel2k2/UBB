namespace MusicalLab2
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            id_matTextBox = new TextBox();
            vechimeTextBox = new TextBox();
            label2 = new Label();
            label3 = new Label();
            insertButton = new Button();
            statusLabel = new Label();
            refolositCheckBox = new CheckBox();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15.75F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(39, 39);
            label1.Name = "label1";
            label1.Size = new Size(180, 30);
            label1.TabIndex = 0;
            label1.Text = "Adauga o coarda";
            // 
            // id_matTextBox
            // 
            id_matTextBox.Location = new Point(114, 125);
            id_matTextBox.Name = "id_matTextBox";
            id_matTextBox.Size = new Size(66, 23);
            id_matTextBox.TabIndex = 1;
            id_matTextBox.TextChanged += id_matTextBox_TextChanged;
            // 
            // vechimeTextBox
            // 
            vechimeTextBox.Location = new Point(114, 154);
            vechimeTextBox.Name = "vechimeTextBox";
            vechimeTextBox.Size = new Size(66, 23);
            vechimeTextBox.TabIndex = 2;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(45, 128);
            label2.Name = "label2";
            label2.Size = new Size(63, 15);
            label2.TabIndex = 4;
            label2.Text = "Id material";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(45, 157);
            label3.Name = "label3";
            label3.Size = new Size(52, 15);
            label3.TabIndex = 5;
            label3.Text = "Vechime";
            // 
            // insertButton
            // 
            insertButton.Location = new Point(105, 241);
            insertButton.Name = "insertButton";
            insertButton.Size = new Size(75, 23);
            insertButton.TabIndex = 8;
            insertButton.Text = "Insert";
            insertButton.UseVisualStyleBackColor = true;
            insertButton.Click += insertButton_Click;
            // 
            // statusLabel
            // 
            statusLabel.AutoSize = true;
            statusLabel.ForeColor = Color.Red;
            statusLabel.Location = new Point(114, 83);
            statusLabel.Name = "statusLabel";
            statusLabel.Size = new Size(0, 15);
            statusLabel.TabIndex = 9;
            // 
            // refolositCheckBox
            // 
            refolositCheckBox.AutoSize = true;
            refolositCheckBox.Location = new Point(108, 192);
            refolositCheckBox.Name = "refolositCheckBox";
            refolositCheckBox.Size = new Size(72, 19);
            refolositCheckBox.TabIndex = 10;
            refolositCheckBox.Text = "Refolosit";
            refolositCheckBox.UseVisualStyleBackColor = true;
            // 
            // Form2
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(269, 276);
            Controls.Add(refolositCheckBox);
            Controls.Add(statusLabel);
            Controls.Add(insertButton);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(vechimeTextBox);
            Controls.Add(id_matTextBox);
            Controls.Add(label1);
            Name = "Form2";
            Text = "Form2";
            Load += Form2_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private TextBox id_matTextBox;
        private TextBox vechimeTextBox;
        private Label label2;
        private Label label3;
        private Button insertButton;
        private Label statusLabel;
        private CheckBox refolositCheckBox;
    }
}