import numpy as np
import plotly.graph_objects as go
import pandas as pd

# pip install plotly pandas

num = 300
x = np.linspace(0,7, num)
y = np.sin(x)*np.exp(-x)


#d = {
#    "x": [str(x[i])+ ' ,' for i in range(0,num)],
#    "y": [str(y[i])+ ' ,' for i in range(0,num)]
#}
#df = pd.DataFrame(d)
#df.to_csv("test.csv")

df = pd.read_csv("build/res.csv")
print(df.keys())

fig = go.Figure()
fig.add_traces( go.Scatter(x=x,y=y, mode="markers", name="init"))
fig.add_traces( go.Scatter(x=x,y=df["y_hat"], mode="markers", name="y_hat"))
fig.show()