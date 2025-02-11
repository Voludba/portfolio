using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

namespace _4labKG
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

		TModel3D cube = new TModel3D("C:\\Users\\Оксана\\Desktop\\дз\\4 семестр\\Графика\\4LabKG\\Lowpoly_tree_sample.obj");
		ZBuffer zb = new ZBuffer(1000, 1000);
		double angle1 = 0, angle2 = 0, angle = 0;
		int x = 100, y = 100, step = 1;


		double zoom = 5;//увеличение кубика
		private void timer1_Tick(object sender, EventArgs e)
		{
			Graphics g = Graphics.FromImage(pictureBox1.Image);
			SolidBrush b = new SolidBrush(Color.White);
			g.FillRectangle(b, 0, 0, pictureBox1.Width, pictureBox1.Height);

			cube.View_transformation(angle2, angle1, angle, x, y, zoom);
			cube.SendToZbuffer(ref zb);

			int kek = 0;

			for (int j = 0; j < zb.sY; j +=  step)
			{
				for (int i = 0; i < zb.sX; i += 2)
					if (zb.buff[i][j].color.Color != Color.White)
					{
						g.DrawLine(zb.buff[i][j].color, i, j, i + 1, j + 1);

					}


			}
			zb.Clear();
			pictureBox1.Invalidate();
		}

		
		// X
		public int posX = -10;
		private void trackBar4_Scroll(object sender, EventArgs e)
		{
			if (trackBar4.Value > posX)
			{
				angle2 += (Math.PI / (360)) * 10 * trackBar4.Value;
				posX = trackBar4.Value;
			}
			if (trackBar4.Value < posX)
			{
				angle2 -= (Math.PI / (360)) * 10 * trackBar4.Value;
				posX = trackBar4.Value;
			}
		}
		// Y
		public int posY = -10;
		private void trackBar3_Scroll(object sender, EventArgs e)
		{
			if (trackBar3.Value > posY)
			{
				angle1 += (Math.PI / (360)) * 10 * trackBar3.Value;
				posY = trackBar3.Value;
			}
			if (trackBar3.Value < posY)
			{
				angle1 -= (Math.PI / (360)) * 10 * trackBar3.Value;
				posY = trackBar3.Value;
			}
		}

        private void button1_Click(object sender, EventArgs e)
        {
			zoom += 1;
		}

        private void button2_Click(object sender, EventArgs e)
        {
			zoom -= 1;
        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
			step++;
        }

        private void button5_Click(object sender, EventArgs e)
        {
			if (step > 1) step--;
        }

        private void button3_Click(object sender, EventArgs e)
        {
				var filePath = string.Empty;

				using (OpenFileDialog openFileDialog = new OpenFileDialog())
				{
					openFileDialog.InitialDirectory = "d:\\";
					openFileDialog.Filter = "obj files (*.obj)|*.obj";
					openFileDialog.FilterIndex = 2;
					openFileDialog.RestoreDirectory = true;

					if (openFileDialog.ShowDialog() == DialogResult.OK)
					{
						//Get the path of specified file
						filePath = openFileDialog.FileName;

					}
				}
				cube.OpenNew(filePath);
		}

        // Z
        public int posZ = -10;
		private void trackBar2_Scroll(object sender, EventArgs e)
		{
			if (trackBar2.Value > posZ)
			{
				angle += (Math.PI / (360)) * 10 * trackBar2.Value;
				posZ = trackBar2.Value;
			}
			if (trackBar2.Value < posZ)
			{
				angle -= (Math.PI / (360)) * 10 * trackBar2.Value;
				posZ = trackBar2.Value;
			}
		}

		void Form1_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyValue == (char)Keys.W)
			{
				x -= 10;
			}
			if (e.KeyValue == (char)Keys.S)
			{
				x += 10;
			}

			if (e.KeyValue == (char)Keys.D)
			{
				y += 10;
			}
			if (e.KeyValue == (char)Keys.A)
			{
				y -= 10;
			}
		}
	}

	struct Cel
	{
		public double z;
		public Pen color;
	};
	class ZBuffer
	{

		public Cel[][] buff;
		public int sX, sY;
		public ZBuffer(int x, int y)
		{
			sX = x; sY = y;
			buff = new Cel[sX][];
			for (int ax = 0; ax < sX; ax++)
			{
				buff[ax] = new Cel[sY];
				for (int ay = 0; ay < sY; ay++)
				{
					buff[ax][ay].z = 10000;
					buff[ax][ay].color = new Pen(Color.White);
				}
			}
		}

		public void Clear()
		{
			for (int ax = 0; ax < sX; ax++)
			{
				for (int ay = 0; ay < sY; ay++)
				{
					buff[ax][ay].z = 10000;
					buff[ax][ay].color.Color = Color.White;
				}
			}


		}

		public void PutPolygon(ref Polygon t)
		{
			int ymax, ymin, ysc, e1, e, i;
			int verNum = t.vertex.Length;
			int[] x = new int[verNum]; int[] y = new int[verNum];
			for (i = 0; i < verNum; i++)
			{
				x[i] = Convert.ToInt32(t.vertex[i].x); y[i] = Convert.ToInt32(t.vertex[i].y);
			}
			ymax = ymin = y[0];
			for (int k = 1; k < verNum; k++)
			{
				if (ymax < y[k]) { ymax = y[k]; } else { if (ymin > y[k]) { ymin = y[k]; } }
			}
			ymin = (ymin < 0) ? 0 : ymin;
			ymax = (ymax < sY) ? ymax : sY;
			bool ne;
			int x1 = 0, x2 = 0, xsc1 = 0, xsc2 = 0;
			double z1 = 0, z2 = 0, tc = 0, z = 0;
			for (ysc = ymin; ysc < ymax; ysc++)
			{
				ne = false;
				for (e = 0; e < verNum; e++)
				{
					e1 = e + 1;
					if (e1 == verNum) { e1 = 0; }
					if (y[e] < y[e1])
					{
						if (y[e1] <= ysc || ysc < y[e]) continue;
					}
					else if (y[e] > y[e1])
					{
						if (y[e1] > ysc || ysc >= y[e]) continue;
					}
					else continue;
					tc = Convert.ToDouble(y[e] - ysc) / (y[e] - y[e1]);
					if (ne)
					{
						x2 = x[e] + Convert.ToInt32(tc * (x[e1] - x[e]));
						z2 = t.vertex[e].z + tc * (t.vertex[e1].z - t.vertex[e].z);
					}
					else
					{
						x1 = x[e] + Convert.ToInt32(tc * (x[e1] - x[e]));
						z1 = t.vertex[e].z + tc * (t.vertex[e1].z - t.vertex[e].z);
						ne = true;
					}

				}
				if (x2 < x1) { e = x1; x1 = x2; x2 = e; tc = z1; z1 = z2; z2 = tc; }
				xsc1 = (x1 < 0) ? 0 : x1;
				xsc2 = (x2 < sX) ? x2 : sX;
				for (int xsc = xsc1; xsc < xsc2; xsc++)
				{
					tc = Convert.ToDouble(x1 - xsc) / (x1 - x2);
					z = z1 + tc * (z2 - z1);
					if (z < (buff[ysc][xsc].z))
					{
						buff[ysc][xsc].color = t.color;
						buff[ysc][xsc].z = z;
					}
				}
			}
		}
	};


	class Polygon
	{
		public Pen color;
		public TPoint3D[] vertex;
//		public List<TPoint3D> vertex = new List<TPoint3D>();
		public Polygon(Pen c, params TPoint3D[] points)
		{
			vertex = new TPoint3D[points.Length];
			for (int i = 0; i < points.Length; i++)
			{
				vertex[i] = points[i];
//				vertex.Add(points[i]);
			}
			color = c;
		}
	}

	class TModel3D
	{
		public List<TPoint3D> Vertexes = new List<TPoint3D>();
		public List<TPoint3D> DrawVertexes = new List<TPoint3D>();
		public List<List<int>> Polygons = new List<List<int>>();
		public List<Pen> VertColors = new List<Pen>();

		public TModel3D(string file_name)
		{
			System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
			string str;
			StreamReader sr = new StreamReader(file_name);
			str = sr.ReadLine();
			List<double> VertCoords = new List<double>();
			int polnum = 0;
			while (str != null)
			{
				if(str.Length > 2)
                {

					if (str[0] == 'v' && str[1] == ' ')
					{
						str = str.Substring(2);
						string[] buff = str.Split(' ');
						foreach (string s in buff)
						{
								double res = Convert.ToDouble(s);
								VertCoords.Add(res);
						}
						Vertexes.Add(new TPoint3D(VertCoords[0], VertCoords[1], VertCoords[2]));
						DrawVertexes.Add(new TPoint3D(VertCoords[0], VertCoords[1], VertCoords[2]));
						VertCoords.Clear();
					}
					else if (str[0] == 'f')
					{
						str = str.Substring(2);
						string[] buff = str.Split(' ');
						Polygons.Add(new List<int>());
						foreach (string s in buff)
						{
							string[] temp = s.Split('/');
							Polygons[polnum].Add(Convert.ToInt16(temp[0]) - 1);
						}
						polnum++;
					}
				}
				str = sr.ReadLine();
			}

		}

		public void OpenNew(string file_name)
        {
			Vertexes.Clear();
			DrawVertexes.Clear();
			Polygons.Clear();
			System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
			string str;
			StreamReader sr = new StreamReader(file_name);
			str = sr.ReadLine();
			List<double> VertCoords = new List<double>();
			int polnum = 0;
			while (str != null)
			{
				if (str.Length > 2)
				{

					if (str[0] == 'v' && str[1] == ' ')
					{
						str = str.Substring(2);
						string[] buff = str.Split(' ');
						foreach (string s in buff)
						{
							double res = Convert.ToDouble(s);
							VertCoords.Add(res);
						}
						Vertexes.Add(new TPoint3D(VertCoords[0], VertCoords[1], VertCoords[2]));
						DrawVertexes.Add(new TPoint3D(VertCoords[0], VertCoords[1], VertCoords[2]));
						VertCoords.Clear();
					}
					else if (str[0] == 'f')
					{
						str = str.Substring(2);
						string[] buff = str.Split(' ');
						Polygons.Add(new List<int>());
						foreach (string s in buff)
						{
							string[] temp = s.Split('/');
							Polygons[polnum].Add(Convert.ToInt16(temp[0]) - 1);
						}
						polnum++;
					}
				}
				str = sr.ReadLine();
			}
		}

		public void View_transformation(double LX, double LY, double LZ, double x, double y, double zoom)
		{
			double x1, y1, z1;
			double x2, y2, z2;
			double x3, y3, z3;
			for (int i = 0; i < Vertexes.Count; i++)
			{
				x1 = Vertexes[i].getx();
				y1 = Vertexes[i].gety() * Math.Cos(LX) + Vertexes[i].getz() * Math.Sin(LX);
				z1 = -Vertexes[i].gety() * Math.Sin(LX) + Vertexes[i].getz() * Math.Cos(LX);

				x2 = x1 * Math.Cos(LY) - z1 * Math.Sin(LY);
				y2 = y1;
				z2 = x1 * Math.Sin(LY) + z1 * Math.Cos(LY);

				x3 = x2 * Math.Cos(LZ) + y2 * Math.Sin(LZ);
				y3 = -x2 * Math.Sin(LZ) + y2 * Math.Cos(LZ);
				z3 = z2;

				x3 += x;
				y3 += y;

				x3 *= zoom;
				y3 *= zoom;
				z3 *= zoom;

				TPoint3D NN = new TPoint3D(x3, y3, z3);
				DrawVertexes[i] = NN;

			}

		}

		public void SendToZbuffer(ref ZBuffer zb)
		{
			Random random = new Random();

			for (int i = 0; i < Polygons.Count; i++)
			{
				TPoint3D[] points = new TPoint3D[Polygons[i].Count];
				for (int k = 0; k < Polygons[i].Count; k++)
				{
					points[k] = DrawVertexes[Polygons[i][k]];
				}
				Pen PolyColor = new Pen(Color.FromArgb(random.Next(250), random.Next(250), random.Next(250)));
				Polygon Poly = new Polygon(PolyColor, points);

				zb.PutPolygon(ref Poly);
			}
		}
	}

	class TPoint3D
	{
		public double x, y, z;

		public TPoint3D(double x, double y, double z)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		}
		public void setx(double value) { x = value; }
		public void sety(double value) { y = value; }
		public void setz(double value) { z = value; }

		public double getx() { return x; }
		public double gety() { return y; }
		public double getz() { return z; }

	};

}
