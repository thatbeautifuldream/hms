import pandas as pd
# import matplotlib.pyplot as plt
# import seaborn as sns
import numpy as np

df = pd.read_csv("heart.csv")
pd.set_option("display.float", "{:.2f}".format)
categorical_val = []
continous_val = []
for column in df.columns:
    # print('==============================')
    # print(f"{column} : {df[column].unique()}")
    if len(df[column].unique()) <= 10:
        categorical_val.append(column)
    else:
        continous_val.append(column)
categorical_val.remove('AHD')
dataset = pd.get_dummies(df, columns = categorical_val)

from sklearn.preprocessing import StandardScaler

s_sc = StandardScaler()
col_to_scale = ['age', 'trestbp', 'chol', 'thalach', 'oldpeak']
dataset[col_to_scale] = s_sc.fit_transform(dataset[col_to_scale])
from sklearn.model_selection import train_test_split

X = dataset.drop('AHD', axis=1)
y = dataset.AHD

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
from sklearn.linear_model import LogisticRegression

regressor = LogisticRegression(solver='liblinear')
regressor.fit(X_train, y_train)
pickle.dump(regressor, open('model.pkl', 'wb'))
model = pickle.load(open('model.pkl', 'rb'))
print(model.predict(X_train))
