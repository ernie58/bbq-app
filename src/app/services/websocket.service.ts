import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs';

@Injectable({ providedIn: 'root' })
export class WebSocketService {
  private socket: WebSocket;
  private messageSubject = new Subject<any>();

  constructor() {
    this.socket = new WebSocket('ws://192.168.3.18:80/');
    this.socket.onmessage = (event) => {
      this.messageSubject.next(JSON.parse(event.data));
    };
  }

  sendMessage(message: any): void {
    this.socket.send(JSON.stringify(message));
  }

  getMessages(): Observable<any> {
    return this.messageSubject.asObservable();
  }
}