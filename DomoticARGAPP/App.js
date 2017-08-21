import React, { Component } from 'react';
import { StyleSheet, AppRegistry, Text, TextInput, View, Button, Alert, Switch,Image } from 'react-native';

export default class PizzaTranslator extends Component {
  constructor(props) {
    super(props);
    this.state = { ip: '192.168.0.24', statusMessage: '' };
  }

  requestLed(num, prender) {
    var URIReq = "";

    if (prender)
      URIReq = "http://" + this.state.ip + "/light" + num + "on";
    else
      URIReq = "http://" + this.state.ip + "/light" + num + "off";

    var xhr = new XMLHttpRequest();
    xhr.open("GET", URIReq, true);
    xhr.setRequestHeader('Cache-Control', 'no-cache');
    xhr.timeout = 5000; // time in milliseconds
    xhr.onload = function () {
      // Request finished. Do processing here.
      console.log("Call " + URIReq + " OK");
    };

    xhr.ontimeout = function (e) {
      console.log("Call " + URIReq + " time out..");
      xhr.abort();
    };
    xhr.send();
  };

  render() {
    return (
      <View style={{ marginTop: 10, flex: 1,alignItems:'center', flexDirection: 'column' }}>
        
        <View style={styles.cover}>
              <Image resizeMode={Image.resizeMode.cover}
            source={require('./img/domoticarg.png')}
          />
        </View>

      <View style={styles.ip}>
        <Text> Ingrese la IP del dispositivo</Text>
        <TextInput
          style={{height: 40, borderColor: 'gray', borderWidth: 1}}
          onChangeText={(ip) => this.setState({ip})}
          value={this.state.ip}
        />
        </View>

        <View style={styles.ip}>
        <Text style={{ fontSize: 20 }}>
          Luz 01
        </Text>

        <Button
          onPress={() => {
            this.setState({ statusMessage: 'activado' });
            this.requestLed(1, true);
          }}
          title="Encender"
        />

        <Button
          style={styles.button}
          onPress={() => {
            this.setState({ statusMessage: 'apagado' });
            this.requestLed(1, false);
          }}
          title="Apagar"
        />
        <Text style={styles.buttonOff}>{this.state.statusMessage}</Text>

        <Text style={{ fontSize: 20 }}>
        Luz 02
        </Text>
        <Button
          onPress={() => {
            this.setState({ statusMessage2: 'activado' });
            this.requestLed(2, true);
          }}
          title="Encender"
        />
        <Button 
          style={styles.button}  
          onPress={() => { 
            this.setState({ statusMessage2: 'apagado' });
            this.requestLed(2, false);
          }}
          title="Apagar"
        />
        <Text style={styles.buttonOff}>{this.state.statusMessage2}</Text>
      </View>

      </View>
        
    );
  }

}

const styles = StyleSheet.create({
  button: {
    flex: 1
  },
  buttonOff: {
    backgroundColor: 'red',
    fontWeight: 'bold',
    color: 'white',
    fontSize: 12
  }
});