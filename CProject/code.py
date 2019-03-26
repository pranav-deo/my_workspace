import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import r2_score
from keras.models import Sequential
from keras.layers import Dense
from keras.callbacks import EarlyStopping
from keras.optimizers import Adam
from keras.layers import LSTM

df = pd.read_csv("maharashtraRainfall.csv")
data = df.values[0:,1:]
data = data.flatten()
timeArray = np.arange('1901-01', '2003-01',  dtype='datetime64[M]')
data = data.reshape(data.shape[0],1)
df = pd.DataFrame({'Rainfall':data[:,0]})
df.insert(0, 'Time', timeArray)
df = df.set_index(['Time'], drop=True)
# print((df))
# plt.figure(figsize=(10, 6))
# df['Rainfall'].plot();
# plt.show()

split_date = pd.Timestamp('1980-01')
df =  df['Rainfall']
train = df.loc[:split_date]
test = df.loc[split_date:]
train = train.values[0:]
test = test.values[0:]
train = (train).reshape((train).shape[0],1)
test = (test).reshape((test).shape[0],1)
# plt.figure(figsize=(10, 6))
# ax = train.plot()
# test.plot(ax=ax)
# plt.legend(['train', 'test']);
# plt.show()

scaler = MinMaxScaler(feature_range=(-1, 1),copy=True)
# train_sc = np.concatenate((train,train),axis = 1)
train_sc = scaler.fit_transform(train)
test_sc = scaler.transform(test)

X_train = train_sc[:-1]
y_train = train_sc[1:]
X_test = test_sc[:-1]
y_test = test_sc[1:]

nn_model = Sequential()
nn_model.add(Dense(12, input_dim=1, activation='relu'))
nn_model.add(Dense(54, activation='relu'))
nn_model.add(Dense(25, activation='relu'))
nn_model.add(Dense(1))
nn_model.compile(loss='mean_squared_error', optimizer='adam')
# early_stop = EarlyStopping(monitor='loss', patience=2, verbose=1)
history = nn_model.fit(X_train, y_train, epochs=100, batch_size=10, verbose=1,  shuffle=True)#callbacks=[early_stop],

y_pred_test_nn = nn_model.predict(X_test)
y_train_pred_nn = nn_model.predict(X_train)
print("The R2 score on the Train set is:\t{:0.3f}".format(r2_score(y_train, y_train_pred_nn)))
print("The R2 score on the Test set is:\t{:0.3f}".format(r2_score(y_test, y_pred_test_nn)))


nn_test_mse = nn_model.evaluate(X_test, y_test, batch_size=1)
print('NN: %f'%nn_test_mse)

nn_y_pred_test = nn_model.predict(X_test)

plt.figure(figsize=(10, 6))
plt.plot(y_test, label='True')
plt.plot(y_pred_test_nn, label='NN')
plt.title("NN's Prediction")
plt.xlabel('Observation')
plt.ylabel('Adj Close Scaled')
plt.legend()
plt.show();

# train_sc_df = pd.DataFrame(train_sc, columns=['Y'], index=train.index)
# test_sc_df = pd.DataFrame(test_sc, columns=['Y'], index=test.index)

# for s in range(1,2):
#     train_sc_df['X_{}'.format(s)] = train_sc_df['Y'].shift(s)
#     test_sc_df['X_{}'.format(s)] = test_sc_df['Y'].shift(s)

# X_train = train_sc_df.dropna().drop('Y', axis=1)
# y_train = train_sc_df.dropna().drop('X_1', axis=1)

# X_test = test_sc_df.dropna().drop('Y', axis=1)
# y_test = test_sc_df.dropna().drop('X_1', axis=1)

# X_train = X_train.as_matrix()
# y_train = y_train.as_matrix()

# X_test = X_test.as_matrix()
# y_test = y_test.as_matrix()

# X_train_lmse = X_train.reshape(X_train.shape[0], X_train.shape[1], 1)
# X_test_lmse = X_test.reshape(X_test.shape[0], X_test.shape[1], 1)

# print('Train shape: ', X_train_lmse.shape)
# print('Test shape: ', X_test_lmse.shape