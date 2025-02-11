using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;


namespace _3labKG
{
    public partial class Form1 : Form
    {   
        public Form1()
        {
            InitializeComponent();
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            timer1.Interval = 10;
            timer1.Start();
        }
        objectz plos = new objectz("C:\\Users\\Оксана\\Desktop\\дз\\4 семестр\\Графика\\3labKG\\circles.bmp");
        double angle1 = 0, angle2 = 0, angle = 0;
        int x = 0, y = 0, z = 0;

        double zoom = 1; int step = 5;

        private void timer1_Tick(object sender, EventArgs e)
        {
            Graphics g = Graphics.FromImage(pictureBox1.Image);
            SolidBrush b = new SolidBrush(Color.White);
            g.FillRectangle(b, 0, 0, pictureBox1.Width, pictureBox1.Height);
            Pen p = new Pen(Color.Black);
            plos.setpov(angle2, angle1, angle, x, y, z);
            int[] line = new int[Convert.ToInt32(plos.size * plos.MNOSHITEL)];
            for (int i = 0; i < Convert.ToInt32(plos.size * plos.MNOSHITEL); i++)
            {
                line[i] = 99999999;
            }
            bool f = true;

            Point setbr = new Point();
            for (int y = Convert.ToInt32(plos.size * plos.MNOSHITEL) - 1; y >= 0; y -= step)
            {
                setbr.X = 0;
                setbr.Y = Convert.ToInt32(y * zoom);
                for (int x = 0; x < Convert.ToInt32(plos.size * plos.MNOSHITEL); x++)
                {

                    if (line[x] > y - plos.prod[x][y].ZI)
                    {

                        if (!f)
                        {
                            setbr.X = Convert.ToInt32(x * zoom);
                            setbr.Y = Convert.ToInt32(y * zoom - plos.prod[x][y].ZI * zoom);
                        }

                        g.DrawLine(p, setbr.X, setbr.Y, Convert.ToInt32(x * zoom), Convert.ToInt32(y * zoom - plos.prod[x][y].ZI * zoom));
                        setbr.X = x * Convert.ToInt32(zoom);
                        setbr.Y = Convert.ToInt32(y * zoom - plos.prod[x][y].ZI * zoom);


                        f = true;
                        line[x] = y - plos.prod[x][y].ZI;
                    }
                    else
                    {
                        f = false;
                    }
                }


            }
            pictureBox1.Invalidate();
        }
        public int pos = -10;

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (trackBar1.Value > pos)
            {
                zoom += trackBar1.Value;
                pos = trackBar1.Value;
            }
            if (trackBar1.Value < pos)
            {
                zoom -= trackBar1.Value;
                pos = trackBar1.Value;
            }
        }
        // X
        public int posX = -10;

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            if (trackBar4.Value > posX)
            {
                angle2 += (Math.PI / (360)) * 10;
                posX = trackBar4.Value;
            }
            if (trackBar4.Value < posX)
            {
                angle2 -= (Math.PI / (360)) * 10;
                posX = trackBar4.Value;
            }
        }


        private void button1_Click(object sender, EventArgs e)
        {

            var filePath = string.Empty;

            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = "c:\\";
                openFileDialog.Filter = "bmp files (*.bmp)|*.bmp|png files (*.png)|*.png";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    //Get the path of specified file
                    filePath = openFileDialog.FileName;

                    //Read the contents of the file into a stream
                    var fileStream = openFileDialog.OpenFile();

                }
            }
            plos.openNew(filePath);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            step++;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (step > 2) step--;
        }

        // Y
        public int posY = -10;
        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            if (trackBar3.Value > posY)
            {
                angle1 += (Math.PI / (360)) * 10;
                posY = trackBar3.Value;
            }
            if (trackBar3.Value < posY)
            {
                angle1 -= (Math.PI / (360)) * 10;
                posY = trackBar3.Value;
            }
        }
        // Z
        public int posZ = -10;
        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            if (trackBar2.Value > posZ)
            {
                angle += (Math.PI / (360)) * 10;
                posZ = trackBar2.Value;
            }
            if (trackBar2.Value < posZ)
            {
                angle -= (Math.PI / (360)) * 10;
                posZ = trackBar2.Value;
            }
        }

    }
    public struct boolint
    {
        public int ZI;
        public bool FLAG;
    }

    class objectz
    {
        public float[][] mas;
        public int size;
        public boolint[][] prod;
        public boolint[][] prodsh;
        public double MNOSHITEL = 2;


        public void openNew(string nameBMP)
        {

            Bitmap srcImage = new Bitmap(nameBMP);

            if (srcImage == null)
                throw new ArgumentNullException("srcImage");

            mas = new float[srcImage.Height][];
            for (var y = 0; y < srcImage.Height; y++)
            {
                mas[y] = new float[srcImage.Width];
                for (var x = 0; x < srcImage.Width; x++)
                {
                    Color srcPixel = srcImage.GetPixel(x, y);
                    mas[y][x] = srcPixel.GetBrightness() * 100 - 150;
                }
            }
            size = srcImage.Height;

            boolint br;
            br.FLAG = false;
            br.ZI = 0;
            prod = new boolint[Convert.ToInt32(size * MNOSHITEL)][];
            for (int i = 0; i < Convert.ToInt32(size * MNOSHITEL); i++)
            {
                prod[i] = new boolint[Convert.ToInt32(size * MNOSHITEL)];
                for (int j = 0; j < Convert.ToInt32(size * MNOSHITEL); j++)
                {
                    prod[i][j] = br;
                }
            }

            prodsh = new boolint[Convert.ToInt32(size * MNOSHITEL)][];
            for (int i = 0; i < Convert.ToInt32(size * MNOSHITEL); i++)
            {
                prodsh[i] = new boolint[Convert.ToInt32(size * MNOSHITEL)];
                for (int j = 0; j < Convert.ToInt32(size * MNOSHITEL); j++)
                {
                    prodsh[i][j] = br;
                }
            }
        }

        public objectz(string nameBMP)
        {
            Bitmap srcImage = new Bitmap(nameBMP);

            if (srcImage == null)
                throw new ArgumentNullException("srcImage");

            mas = new float[srcImage.Height][];
            for (var y = 0; y < srcImage.Height; y++)
            {
                mas[y] = new float[srcImage.Width];
                for (var x = 0; x < srcImage.Width; x++)
                {
                    Color srcPixel = srcImage.GetPixel(x, y);
                    mas[y][x] = srcPixel.GetBrightness() * 100 - 150;
                }
            }
            size = srcImage.Height;

            boolint br;
            br.FLAG = false;
            br.ZI = 0;
            prod = new boolint[Convert.ToInt32(size * MNOSHITEL)][];
            for (int i = 0; i < Convert.ToInt32(size * MNOSHITEL); i++)
            {
                prod[i] = new boolint[Convert.ToInt32(size * MNOSHITEL)];
                for (int j = 0; j < Convert.ToInt32(size * MNOSHITEL); j++)
                {
                    prod[i][j] = br;
                }
            }

            prodsh = new boolint[Convert.ToInt32(size * MNOSHITEL)][];
            for (int i = 0; i < Convert.ToInt32(size * MNOSHITEL); i++)
            {
                prodsh[i] = new boolint[Convert.ToInt32(size * MNOSHITEL)];
                for (int j = 0; j < Convert.ToInt32(size * MNOSHITEL); j++)
                {
                    prodsh[i][j] = br;
                }
            }

        }

        public void setpov(double px, double py, double pz, int rx, int ry, int rz)
        {

            for (int x = 0; x < size * MNOSHITEL; x++)
            {
                for (int y = 0; y < size * MNOSHITEL; y++)
                {
                    prod[x][y] = prodsh[x][y];
                }
            }
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {

                    double x1, y1, z1;
                    x1 = x - (size / 2);
                    y1 = (y - (size / 2)) * Math.Cos(px) + (mas[x][y] - (size / 2)) * Math.Sin(px);
                    z1 = -(y - (size / 2)) * Math.Sin(px) + (mas[x][y] - (size / 2)) * Math.Cos(px);

                    double x2, y2, z2;
                    x2 = x1 * Math.Cos(py) - z1 * Math.Sin(py);
                    y2 = y1;
                    z2 = x1 * Math.Sin(py) + z1 * Math.Cos(py);

                    double x3, y3, z3;
                    x3 = x2 * Math.Cos(pz) + y2 * Math.Sin(pz);
                    y3 = -z2 * Math.Sin(pz) + y2 * Math.Cos(pz);
                    z3 = z2;

                    boolint vr;
                    vr.ZI = Convert.ToInt32(z3 + rz + ((size * MNOSHITEL) / 2));
                    vr.FLAG = true;
                    prod[Convert.ToInt32(x3 + rx + ((size * MNOSHITEL) / 2))][Convert.ToInt32(y3 + ry + ((size * MNOSHITEL) / 2))] = vr;

                }
            }



        }

    };
}
