import React, { Component } from 'react';
import {StyleSheet, AppRegistry, Text, TextInput, View,Button, Alert } from 'react-native';

export default class PizzaTranslator extends Component {
  constructor(props) {
    super(props);
    this.state = {ip: '', statusMessage: ''};
  }
  
  render() {
    return (
      <View style={{marginTop: 100, flex:1, flexDirection:'column'}}>
        <TextInput
          style={{height: 40}}
          name="ip"
          placeholder="Type the IP Address (default is 192.168.0.26)"
          onChangeText={(text) => this.setState({ip: text})}
        />
     <Button
        onPress={() => { 
                          this.setState({statusMessage: 'activado'});
                          requestLed(1);
                        }}
          title="Encender"
      />
       <Button
        style={styles.button}
        onPress={() => { 
                          this.setState({statusMessage: 'apagado'});
                          requestLed(0);
                        }}
          title="Apagar"
      />
              <Text style={styles.buttonOff}>{this.state.statusMessage}</Text>

        </View>
    );
  }
  
}

const styles = StyleSheet.create({
  button:{
    flex: 1
  },
  buttonOff: {
    backgroundColor: 'red',
    fontWeight: 'bold',
    color: 'white',
    fontSize: 12
  }
});

  function requestLed(num) {
    //this.setState({statusMessage: 'activado'});
    var request = new XMLHttpRequest();
  request.onreadystatechange = (e) => {
  if (request.readyState !== 4) {
    return;
  }

  if (request.status === 200) {
    console.log('success', request.responseText);
  } else {
    console.warn('error');
  }
};

request.open('GET', 'http://192.168.0.26/led=' + String(num));
request.send();
  }